#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ICMP_SIZE (sizeof(struct icmp))
#define ICMP_ECHO 8
#define ICMP_ECHOREPLY 0
#define BUF_SIZE 1024
#define NUM   5    // 发送报文次数

#define UCHAR  unsigned char
#define USHORT unsigned short
#define UINT   unsigned int 

// ICMP报文数据结构
struct icmp{
    UCHAR           type;      // 类型
    UCHAR           code;      // 代码
    USHORT          checksum;  // 校验和
    USHORT          id;        // 标识符
    USHORT          sequence;  // 序号 
    struct timeval  timestamp; // 时间戳
};


// IP首部数据结构
struct ip{
    // 主机字节序判断
    #if __BYTE_ORDER == __LITTLE_ENDIAN
    UCHAR   hlen:4;        // 首部长度
    UCHAR   version:4;     // 版本      
    #endif
    #if __BYTE_ORDER == __BIG_ENDIAN
    UCHAR   version:4;       
    UCHAR   hlen:4;    
    #endif    
    UCHAR   tos;             // 服务类型
    USHORT  len;             // 总长度
    USHORT  id;                // 标识符
    USHORT  offset;            // 标志和片偏移
    UCHAR   ttl;            // 生存时间
    UCHAR   protocol;       // 协议
    USHORT  checksum;       // 校验和
    struct in_addr ipsrc;    // 32位源ip地址
    struct in_addr ipdst;   // 32位目的ip地址
};


char buf[BUF_SIZE] = {0};

USHORT checkSum(USHORT *, int); // 计算校验和
float timediff(struct timeval *, struct timeval *); // 计算时间差
void pack(struct icmp *, int);  // 封装一个ICMP报文
int unpack(char *, int, char *);        // 对接收到的IP报文进行解包


int main(int argc, char * argv[]){
    struct hostent *host;
    struct icmp sendicmp;
    struct sockaddr_in from;
    struct sockaddr_in to;
    int fromlen = 0;
    int sockfd;
    int nsend = 0;
    int nreceived = 0;
    int i, n;
    in_addr_t inaddr;

    memset(&from, 0, sizeof(struct sockaddr_in));
    memset(&to, 0, sizeof(struct sockaddr_in));

    if(argc < 2){
        printf("use : %s hostname/IP address \n", argv[0]);
        exit(1);
    }

    // 生成原始套接字
    if((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1){
        printf("socket() error \n");
        exit(1);
    }

    // 设置目的地址信息
    to.sin_family = AF_INET;

    // 判断是域名还是ip地址
    if(inaddr = inet_addr(argv[1]) == INADDR_NONE){
        // 是域名
        if((host = gethostbyname(argv[1])) == NULL){
            printf("gethostbyname() error \n");
            exit(1);
        }
        to.sin_addr = *(struct in_addr *)host->h_addr_list[0];
    }else{
        // 是ip地址
        to.sin_addr.s_addr = inaddr;
    }

    // 输出域名ip地址信息
    printf("ping %s (%s) : %d bytes of data.\n", argv[1], inet_ntoa(to.sin_addr), (int)ICMP_SIZE);

    //循环发送报文、接收报文 
    for(i = 0; i < NUM; i++){
        printf("\n");
        nsend++;  // 发送次数加1
        memset(&sendicmp, 0, ICMP_SIZE);
        pack(&sendicmp, nsend);

        // 发送报文
        if(sendto(sockfd, &sendicmp, ICMP_SIZE, 0, (struct sockaddr *)&to, sizeof(to)) == -1){
            printf("sendto() error \n");
            continue;
        }
        
        // 接收报文
        if((n = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&from, &fromlen)) < 0){
            printf("recvform() error \n");
            continue;
        }
        printf("buf: %s\n", buf);

        nreceived++;  // 接收次数加1
        if(unpack(buf, n, inet_ntoa(from.sin_addr)) == -1){
            printf("unpack() error \n");
        }

        sleep(1);
    }

    // 输出统计信息
    printf("---  %s ping statistics ---\n", argv[1]);
    printf("%d packets transmitted, %d received, %%%d packet loss\n", nsend, nreceived, 
            (nsend - nreceived) / nsend * 100);

    return 0;
}

/**
 * addr 指向需校验数据缓冲区的指针
 * len  需校验数据的总长度（字节单位）
 */
USHORT checkSum(USHORT *addr, int len){
    UINT sum = 0;  
    while(len > 1){
        sum += *addr++;
        len -= 2;
    }

    // 处理剩下的一个字节
    if(len == 1){
        sum += *(UCHAR *)addr;
    }

    // 将32位的高16位与低16位相加
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (USHORT) ~sum;
}

/**
 * 返回值单位：ms
 * begin 开始时间戳
 * end   结束时间戳
 */
float timediff(struct timeval *begin, struct timeval *end){
    int n;
    // 先计算两个时间点相差多少微秒
    n = ( end->tv_sec - begin->tv_sec ) * 1000000
        + ( end->tv_usec - begin->tv_usec );

    // 转化为毫秒返回
    return (float) (n / 1000);
}

/**
 * icmp 指向需要封装的ICMP报文结构体的指针
 * sequence 该报文的序号
 */ 
void pack(struct icmp * icmp, int sequence){
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->id = getpid();
    icmp->sequence = sequence;
    gettimeofday(&icmp->timestamp, 0);
    icmp->checksum = checkSum((USHORT *)icmp, ICMP_SIZE);
}

/**
 * buf  指向接收到的IP报文缓冲区的指针
 * len  接收到的IP报文长度
 * addr 发送ICMP报文响应的主机IP地址
 */ 
int unpack(char * buf, int len, char * addr){
   int i, ipheadlen;
   struct ip * ip;
   struct icmp * icmp;
   float rtt;          // 记录往返时间
   struct timeval end; // 记录接收报文的时间戳
   
   ip = (struct ip *)buf;

   // 计算ip首部长度，即ip首部的长度标识乘4
   ipheadlen = ip->hlen << 2;
    
   // 越过ip首部，指向ICMP报文
   icmp = (struct icmp *)(buf + ipheadlen);
   printf("icmp all info\n");
   printf("type: %u; code: %u; checksum: %hu\n", 
            icmp->type, icmp->code, icmp->checksum);
   printf("id: %hu; sequence: %hu; timestamp: %ld\n",
            icmp->id, icmp->sequence, (icmp->timestamp).tv_sec);

   // ICMP报文的总长度
   len -= ipheadlen;

   // 如果小于ICMP报文首部长度8
   if(len < 8){
        printf("ICMP packets\'s length is less than 8 \n"); 
        return -1;
   }

   printf("icmp-type/ICMP_ECHOREPLY: %d %d\n", icmp->type, ICMP_ECHOREPLY);
  printf("icmp-id/getpid(): %d %d\n", icmp->id, getpid()); 
   // 确保是我们所发的ICMP ECHO回应
   if(icmp->type != ICMP_ECHOREPLY ||
           icmp->id != getpid()){    
       printf("ICMP packets are not send by us \n");
       return -1;
   }

   // 计算往返时间
   gettimeofday(&end, 0);
   rtt = timediff(&icmp->timestamp, &end);

   // 打印ttl，rtt，seq
   printf("%d bytes from %s : icmp_seq=%u ttl=%d rtt=%fms \n",
           len, addr, icmp->sequence, ip->ttl, rtt);

   return 0;
}

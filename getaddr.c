#include <libnet.h>

int main(int argc,char *argv[]){
	int c;
	u_long i;
	libnet_t *l;
	char *device = NULL;
	struct libnet_ether_addr *e;
	char errbuf[LIBNET_ERRBUF_SIZE];

	printf("libnet 1.1 address getter\n");

	while((c = getopt(argc,argv,"i:")) != EOF){
		switch(c){
			case 'i':
				device = optarg;
				break;
			default:
				exit(EXIT_FAILURE);
		}
	}

	//Initialize the library.Root Priviledges are requried.
	l = libnet_init(
			LIBNET_LINK,		/* injection type */
			device,				/* network interface */
			errbuf);			/* errbuf */

	if(l == NULL){
		fprintf(stderr,"libnet_init() failed:%s",errbuf);
		exit(EXIT_FAILURE);
	}

	printf("Interface:\t%s\n",libnet_getdevice(l));
	e = libnet_get_hwaddr(l);
	if(e == NULL){
		fprintf(stderr,"Can't get hardware address:%s\n",libnet_geterror(l));
	}else{
		printf("MAC address:\t");
		for(c=0;c < 6;c++){
			printf("%2.2x",e->ether_addr_octet[c]);
			if(c !=5 )
				printf(":");
		}
		printf("\n");
	}
}



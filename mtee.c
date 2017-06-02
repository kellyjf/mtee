#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <time.h>

void usage(const char *program) {

        fprintf(stderr, "Usage %s [options] [teefile]\n"
"     Options:\n"
"     -i identifier       Target name for label\n"
"     -t tformat          strftime format for label [default %H:%M:%S]\n", program);
}       
int main(int argc, char **argv) {
        char              *opt_tfmt    = "%H:%M:%S";
        char              *opt_ident   = "";
        char               arg         = 0;
	int                opt_full    = 0;
	char              *opt_filemode="w+";
	FILE              *foutput     = NULL;
	static unsigned char  buffer[8192];
	static unsigned char  header[256];
	static unsigned char  hdr_fmt[256];

        struct option  options[] = {
                { "ident",     required_argument, NULL, 'i' },
                { "append",    required_argument, NULL, 'a' },
                { "tfmt",      required_argument, NULL, 't' },
                { "help",      no_argument,       NULL, 'h' },
                { NULL } 
        };

       while((arg=getopt_long(argc, argv, "t:i:ha", options, NULL)) != -1) {
                switch(arg) {

                case 'i':
                        opt_ident= optarg;
                        break;

                case 't':
                        opt_tfmt= optarg;
                        break;

                case 'h':
                        usage(argv[0]);
                        return(0);

                case 'a':
			opt_filemode="a+";
			break;

                default:
                        usage(argv[0]);
                        return(1);
                }
        }

        if(optind<argc) {
                char *filename = argv[optind];

                if((foutput=fopen(filename, opt_filemode))==NULL) {
                        perror(filename);
                        return(2);
                }

        }

	if(!opt_full && opt_ident) {
		char *start = strrchr(opt_ident, '/');
		if (start) opt_ident = start+1;
	}

	sprintf(hdr_fmt, "%s [%s] ", opt_tfmt, opt_ident);

	while(fgets(buffer, sizeof(buffer), stdin)) {
		time_t     t  = time(NULL);
		struct tm *tm = localtime(&t);
		strftime(header, sizeof(header), hdr_fmt, tm);
		fprintf(stdout, "%s%s", header, buffer);
		fflush(stdout);
		if(foutput) {
			fprintf(foutput, "%s%s", header, buffer);
			fflush(foutput);
		}
	}

	if(foutput) fclose(foutput);
        return(0);
}

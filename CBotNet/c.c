#include "constants.h"
#include "debug.h"
#include "wrappers.h"

int bot_num = 0;
struct sockaddr bots[MAX_BOTS];

struct addr_4 {
    char ip[INET_ADDRSTRLEN];
    char port[22];
};

struct MSG {
    char command;
    struct addr_4 targets[20];
};

void print_usage() {
    errx(1,
         "Usage: ./CandC [tcp_port]\n"
         "tcp_port \tnaziv ili broj TCP porta na kojem sluša C&C "
         "poslužitelj (pretpostavljena vrijednost je 80)");
}

struct arguments {
    uint16_t tcp_port;
} args = {80};

void parse_arguments(int argc, char* argv[], int num_required_pos) {
    if ((argc - optind) == 1) args.tcp_port = parse_port(argv[optind++]);

    if ((argc - optind) != num_required_pos) print_usage();

    dbgprint(
        "=== parsed arguments ===\n"
        "tcp_port: %d\n"
        "========================\n",
        args.tcp_port);

    return;
}

void print_bots() {
    for (int i = 0; i < bot_num; i++) {
        char ip[NI_MAXHOST];
        char port[NI_MAXSERV];
        saddr_to_ipport(bots[i], ip, port);
        printf("%s:%s;", ip, port);
    }
    printf("\n");
}

void print_help() {
    printf("Podržane su naredbe:\n");
    printf(
        "pt \tbot klijentima šalje poruku PROG_TCP (struct MSG:1 10.0.0.20 "
        "1234\\n)\n");
    printf(
        "ptl \tbot klijentima šalje poruku PROG_TCP (struct MSG:1 127.0.0.1 "
        "1234\\n)\n");
    printf(
        "pu \tbot klijentima šalje poruku PROG_UDP (struct MSG:2 10.0.0.20 "
        "1234\\n)\n");
    printf(
        "pul \tbot klijentima šalje poruku PROG_UDP (struct MSG:2 127.0.0.1 "
        "1234\\n\n");
    printf(
        "r \tbot klijentima šalje poruku RUN s adresama lokalnog računala:\n"
        " \tstruct MSG:3 127.0.0.1 vat localhost 6789\n");
    printf(
        "r2 \tbot klijentima šalje poruku RUN s adresama računala iz "
        "IMUNES-a:\n "
        "\tstruct MSG:3 20.0.0.11 1111 20.0.0.12 2222 20.0.0.13 dec-notes\n");
    printf("s \tbot klijentima šalje poruku STOP (struct MSG:4)\n");
    printf("l \tlokalni ispis adresa bot klijenata\n");
    printf("n \tšalje poruku: ’NEPOZNATA’\\n\n");
    printf(
        "q \tbot klijentima šalje poruku QUIT i završava s radom (struct "
        "MSG:0)\n");
    printf("h \tispis naredbi\n");
}

void send_message(int sockfd, struct MSG msg, int num_targets) {
    for (int i = 0; i < bot_num; i++) {
        int err =
            sendto(sockfd, &msg, 1 + (sizeof(struct addr_4) * num_targets), 0,
                   &bots[i], sizeof(bots[i]));

        if (err < 0) {
            dbgprint("failed sending message: %s\n", strerror(errno));
            char ip[NI_MAXHOST];
            char port[NI_MAXSERV];
            saddr_to_ipport(bots[i], ip, port);
            dbgprint("offending bot: %s:%s\n", ip, port);
        }
    }
}

int handle_request(int sockfd) {
    char request[65536], response[65536];
    bzero(request, sizeof request);

    Recv(sockfd, request, sizeof request, 0);

    if (strncmp(request, "GET ", 4)) {
        makenotallowed(response);
        Write(sockfd, response, strlen(response));
        return 0;
    }

    for (int i = 4; i < 65536; i++) {
        if (request[i] == ' ') {
            request[i] = 0;
            break;
        }
    }

    char requested_path[65536];
    strcpy(requested_path, request + 5);
    dbgprint("requested path: %s\n", requested_path);

    if (!strcmp(requested_path, "bot/prog_tcp")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 3;
    } else if (!strcmp(requested_path, "bot/prog_tcp_localhost")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 1;
    } else if (!strcmp(requested_path, "bot/prog_udp")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 4;
    } else if (!strcmp(requested_path, "bot/prog_udp_localhost")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 2;
    } else if (!strcmp(requested_path, "bot/run")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 6;
    } else if (!strcmp(requested_path, "bot/run2")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 5;
    } else if (!strcmp(requested_path, "bot/stop")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 7;
    } else if (!strcmp(requested_path, "bot/list")) {
        return 8;
    } else if (!strcmp(requested_path, "bot/quit")) {
        makehtmlresponse(response, "OK", "OK");
        Write(sockfd, response, strlen(response));
        return 9;
    } else {
        int dot = -1;
        for (unsigned int i = 0, cnt = 0; i < strlen(requested_path); i++) {
            if (requested_path[i] == '.') {
                dot = i;
                cnt++;
            }
            if (cnt > 1) {
                makeforbidden(response);
                Write(sockfd, response, strlen(response));
                return 0;
            }
        }
        if (dot == -1) {
            makenotfound(response);
            Write(sockfd, response, strlen(response));
            return 0;
        }

        char extension[65536];
        strcpy(extension, requested_path + dot + 1);

        FILE* fp = fopen(requested_path, "rb");
        if (!fp) {
            if (errno == EACCES) {
                makeforbidden(response);
                Write(sockfd, response, strlen(response));
                return 0;
            } else {
                makenotfound(response);
                Write(sockfd, response, strlen(response));
                return 0;
            }
        }

        fseek(fp, 0, SEEK_END);
        long bytes = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        if (!strcicmp(extension, "html"))
            makefileresponse(response, bytes, "text/html");
        else if (!strcicmp(extension, "txt"))
            makefileresponse(response, bytes, "text/plain");
        else if (!strcicmp(extension, "gif"))
            makefileresponse(response, bytes, "image/gif");
        else if (!strcicmp(extension, "jpg"))
            makefileresponse(response, bytes, "image/jpg");
        else if (!strcicmp(extension, "pdf"))
            makefileresponse(response, bytes, "application/pdf");
        else {
            makenotallowed(response);
            Write(sockfd, response, strlen(response));
            return 0;
        }
        Send(sockfd, response, strlen(response), 0);

        char data[BLOCK_SIZE] = {0};

        int nread = 1;
        while (nread) {
            nread = 0;
            nread = fread(data, 1, BLOCK_SIZE - nread, fp);
            Send(sockfd, data, sizeof(data), 0);
            bzero(data, sizeof(data));
        }
        fclose(fp);
    }

    return 0;
}

void makemsg(struct MSG* msg, char command, int numtargets, ...) {
    va_list valist;
    va_start(valist, numtargets);

    msg->command = command;
    for (int i = 0; i < numtargets; i++) {
        struct addr_4 target;
        char* ip = va_arg(valist, char*);
        char* port = va_arg(valist, char*);
        strncpy(target.ip, ip, strlen(ip) + 1);
        strncpy(target.port, port, strlen(port) + 1);
        msg->targets[i] = target;
    }

    va_end(valist);
}

int main(int argc, char* argv[]) {
    dbgprint("run CandC\n");
    parse_arguments(argc, argv, 0);

    int tcpsocket = Socket(args.tcp_port, SOCK_STREAM);
    int udpsocket = Socket(UDP_PORT, SOCK_DGRAM);

    Listen(tcpsocket, 30);
    struct pollfd fds[4];
    memset(fds, 0, sizeof(fds));
    bzero(bots, sizeof bots);

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;
    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;
    fds[2].fd = udpsocket;
    fds[2].events = POLLIN | POLLOUT;
    fds[3].fd = tcpsocket;
    fds[3].events = POLLIN;

    struct MSG messages[100];
    for (int i = 0; i < 100; i++) bzero(&messages[i], sizeof messages[i]);
    int list = 0;
    int help = 0;
    int messageslen = 0;
    int numtargets = 0;
    int isnepoznata = 0;
    for (;;) {
        int rc = poll(fds, 4, -1);

        if (rc < 0) errx(22, "poll failed");

        // STDIN
        if (fds[0].revents & POLLIN) {
            char buffer[1024];
            bzero(buffer, 1024);
            if (read(STDIN_FILENO, buffer, sizeof(buffer)) == -1) {
                errx(1, "recv stdin error");
            }

            // PROG_TCP 2
            if (!strncmp(buffer, "ptl", 3)) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '1', numtargets, "127.0.0.1",
                        "1234");
            }
            // PROG_UDP 2
            else if (!strncmp(buffer, "pul", 3)) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '2', numtargets, "127.0.0.1",
                        "1234");
            }
            // PROG_TCP
            else if (!strncmp(buffer, "pt", 2)) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '1', numtargets, "10.0.0.20",
                        "1234");
            }
            // PROG_UDP
            else if (!strncmp(buffer, "pu", 2)) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '2', numtargets, "10.0.0.20",
                        "1234");
            }
            // RUN 2
            else if (!strncmp(buffer, "r2", 2)) {
                numtargets = 3;
                makemsg(&messages[messageslen++], '3', numtargets, "20.0.0.11",
                        "1111", "20.0.0.12", "2222", "20.0.0.13", "dec-notes");
            }
            // RUN
            else if (!strncmp(buffer, "r", 1)) {
                numtargets = 2;
                makemsg(&messages[messageslen++], '3', numtargets, "127.0.0.1",
                        "vat", "localhost", "6789");
            }
            // STOP
            else if (!strncmp(buffer, "s", 1)) {
                makemsg(&messages[messageslen++], '4', 0);
            }
            // LIST
            else if (!strncmp(buffer, "l", 1)) {
                dbgprint("--> LIST\n");
                list = 1;
            }
            // NEPOZNATA\n
            else if (!strncmp(buffer, "n", 1)) {
                isnepoznata = 1;
            }
            // QUIT
            else if (!strncmp(buffer, "q", 1)) {
                makemsg(&messages[messageslen++], '0', 0);
            }
            // HELP
            else if (!strncmp(buffer, "h", 1)) {
                dbgprint("--> HELP\n");
                help = 1;
            }
        }

        // STDOUT
        if (fds[1].revents & POLLOUT) {
            if (list) {
                print_bots();
                list = 0;
            }
            if (help) {
                print_help();
                help = 0;
            }
        }

        // UDP SOCKET
        if (fds[2].revents & POLLIN) {
            char buffer[5];
            struct sockaddr addr;
            socklen_t addr_len = sizeof addr;
            bzero(buffer, 5);

            if (recvfrom(udpsocket, buffer, sizeof(buffer), 0, &addr,
                         &addr_len) == -1) {
                errx(2, "recv udp error");
            }

            if (!strncmp(buffer, "REG\n", 4) && bot_num < MAX_BOTS) {
                dbgprint("recv REG\n");
                bots[bot_num++] = addr;
                if (bot_num == MAX_BOTS - 1) {
                    dbgprint(
                        "WARNING max bots reached, new bots won't register\n");
                }
                char ip[NI_MAXHOST];
                char port[NI_MAXSERV];
                saddr_to_ipport(addr, ip, port);
                dbgprint("Register bot %s:%s \n", ip, port);
            }
        }

        if (fds[2].revents & POLLOUT) {
            if (messageslen) {
                messageslen--;
                struct MSG msg = messages[messageslen];
                send_message(udpsocket, msg, numtargets);

                // QUIT
                if (msg.command == '0') {
                    close(tcpsocket);
                    close(udpsocket);
                    exit(0);
                }

                bzero(&msg, sizeof msg);
                numtargets = 0;
            }
            if (isnepoznata) {
                isnepoznata = 0;
                char* buff = "NEPOZNATA\n";
                for (int i = 0; i < bot_num; i++)
                    sendto(udpsocket, buff, strlen(buff), 0, &bots[i],
                           sizeof bots[i]);
            }
        }

        // TCP SOCKET
        if (fds[3].revents & POLLIN) {
            int newtcp = Accept(tcpsocket);
            int command = handle_request(newtcp);
            // PROG_TCP 2
            if (command == 1) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '1', numtargets, "127.0.0.1",
                        "1234");
            }
            // PROG_UDP 2
            else if (command == 2) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '2', numtargets, "127.0.0.1",
                        "1234");
            }
            // PROG_TCP
            else if (command == 3) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '1', numtargets, "10.0.0.20",
                        "1234");
            }
            // PROG_UDP
            else if (command == 4) {
                numtargets = 1;
                makemsg(&messages[messageslen++], '2', numtargets, "10.0.0.20",
                        "1234");
            }
            // RUN 2
            else if (command == 5) {
                numtargets = 3;
                makemsg(&messages[messageslen++], '3', numtargets, "20.0.0.11",
                        "1111", "20.0.0.12", "2222", "20.0.0.13", "dec-notes");
            }
            // RUN
            else if (command == 6) {
                numtargets = 2;
                makemsg(&messages[messageslen++], '3', numtargets, "127.0.0.1",
                        "vat", "localhost", "6789");
            }
            // STOP
            else if (command == 7) {
                makemsg(&messages[messageslen++], '4', 0);
            }
            // LIST
            else if (command == 8) {
                char response[65536];

                char botstring[65536];
                botstring[0] = 0;

                strcat(botstring, "<ul>");
                for (int i = 0; i < bot_num; i++) {
                    char ip[NI_MAXHOST];
                    char port[NI_MAXSERV];
                    saddr_to_ipport(bots[i], ip, port);
                    strcat(botstring, "<li>");
                    strcat(botstring, ip);
                    strcat(botstring, ":");
                    strcat(botstring, port);
                    strcat(botstring, "</li>");
                }
                strcat(botstring, "</ul>");

                makehtmlresponse(response, "Bot list", botstring);
                Write(newtcp, response, strlen(response));
            }
            // QUIT
            else if (command == 9) {
                makemsg(&messages[messageslen++], '0', 0);
            }
            close(newtcp);
        }
    }
}

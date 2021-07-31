FROM ubuntu:18.04
ENV HOME /root
RUN id
RUN apt-get update
RUN apt-get install -y gcc make socat gdbserver
RUN groupadd --gid 995 monsec
RUN useradd -m --uid 995 --gid 995 monsec2
COPY 2/ /opt/2
COPY glibc /opt/glibc
WORKDIR /opt/2
RUN make
RUN chmod +x start.sh
EXPOSE 8888:8888
USER monsec2
CMD ["./start.sh"]

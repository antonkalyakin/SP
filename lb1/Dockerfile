FROM amazonlinux:2
ADD ./test.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/test.sh
RUN yum install -y yum-utils
CMD ["/usr/local/bin/test.sh"]

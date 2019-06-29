FROM alpine:3.8 AS builder
RUN apk add --no-cache gcc libc-dev make
WORKDIR /home/c-websrv
COPY . .
RUN cd src && make

FROM alpine AS release
COPY --from=builder /home/c-websrv/bin /
COPY ./index.html /
CMD ["/c-webserv"]

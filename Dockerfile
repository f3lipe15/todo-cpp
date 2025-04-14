FROM gcc:13

WORKDIR /app

COPY main.cpp .
RUN g++ main.cpp -o todo

CMD ["./todo"]

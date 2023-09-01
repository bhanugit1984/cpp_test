FROM gcc:latest

COPY . /usr/src/cpp_test

WORKDIR /usr/src/cpp_test

RUN g++ -o Test Bank.cpp

CMD [ "./Test" ]

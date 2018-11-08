FROM gcc:4.9
COPY . /cam_hsq_test
WORKDIR /cam_hsq_test
RUN g++ -o RobHill RobHill.cpp
CMD ["./RobHill", "./input.csv", "./output.csv"]

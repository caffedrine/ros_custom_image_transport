#Mesaj personalizat ce include Imaginea + Datele de pe IMU

#Imaginea ca urmeaza a fi transmisa
sensor_msgs/Image image

#Optional: timestamp - folosit pentru a vedea timpul necesar transmiterii imaginii in nodul urmator
#std_msgs/Header header //Exista deja imagine.

#Datele de pe IMU
uint32 imu_x
uint32 imu_y
uint32 imu_z


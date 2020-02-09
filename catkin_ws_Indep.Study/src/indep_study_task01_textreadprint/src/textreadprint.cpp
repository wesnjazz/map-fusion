#include <ros/ros.h>
#include <std_msgs/String.h>
#include <fstream>

int usage(char *app_name) {
    std::cout << "Usage: " << app_name << " [text file]\n";
    std::cout << "Options:\n";
    std::cout << "  -p\t\t\tpause on every line\n\n";
    exit(0);
}

int main(int argc, char **argv)
{
    // Initialize to use ROS system passing argc and argv with the name of the node
    ros::init(argc, argv, "textreadprint_node");

    // Main access point to communications with the ROS system.
    // First NodeHandle constructed fully initialize this node
    // Last NodeHandle decunstructed close down this node
    ros::NodeHandle n;

    // Check number of arguments
    if (argc < 2 || 3 < argc) {
        usage(argv[0]);
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cout << "The file [" << argv[1] << "] doesn't exists.\n\n";
        exit(0);
    }
    bool pause = false;

    // Detect pause option
    if (argc == 3) {
        std::string option_p(argv[2]);
        if (option_p.compare("-p") == 0) {
            pause = true;
        } else {
            usage(argv[0]);
        }
    }
    
    // Print text file line by line
    std::string line;
    // std::flush();
    while(std::getline(infile, line)) {
        std::cout << line << std::endl;
        if (pause) {
            std::getchar();
        }
    }

    infile.close();
    return 0;
}
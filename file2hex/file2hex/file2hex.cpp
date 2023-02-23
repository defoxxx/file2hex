#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        return 1;
    }

    std::ifstream input(argv[1], std::ios::binary);
    if (!input)
    {
        std::cerr << "Failed to open file " << argv[1] << "\n";
        return 1;
    }

    // Construct output file path
    std::string output_path(argv[1]);
    output_path += ".txt";

    std::ofstream output(output_path);
    if (!output)
    {
        std::cerr << "Failed to create output file " << output_path << "\n";
        return 1;
    }

    // Convert file contents to hex and write to output file
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setfill('0');
    unsigned char byte;
    while (input.read(reinterpret_cast<char*>(&byte), sizeof(byte)))
    {
        oss << "0x" << std::setw(2) << static_cast<int>(byte) << " ";
    }
    output << oss.str() << "\n";

    std::cout << "File converted and saved to " << output_path << "\n";
    return 0;
}
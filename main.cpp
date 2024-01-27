#include <iostream>
#include <sstream>

int Solve();

int main(int argc, char** argv){
    std::string InStr;
    for(int i = 1; i < argc; ++i)
    {
        InStr += argv[i];
        InStr += " ";
    }

    std::istringstream InBuf(InStr);
    auto CinBuf = std::cin.rdbuf();
    std::cin.rdbuf(InBuf.rdbuf());

    auto CoutBuf = std::cout.rdbuf();
    std::ostringstream OutBuf;
    std::cout.rdbuf(OutBuf.rdbuf());

    Solve();

    std::cout.rdbuf(CoutBuf);
    std::string Str = OutBuf.str();
    std::string::size_type Pos = 0;
    while((Pos = Str.find("\n", Pos)) != std::string::npos)
    {
        Str.insert(Pos + 1, "\t");
        Pos += 2;
    }
    std::cout << "\t" << Str << std::endl;
}

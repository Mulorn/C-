#include <iostream>
#include <algorithm>
using namespace std;

int sorting()
{
    int score[4], clear = -1;
    ifstream in("resources/Firstplace.TXT");
    in >> score[0];
    in.close();

    ifstream in_("resources/Secondplace.TXT");
    in_ >> score[1];
    in_.close();

    ifstream in__("resources/Thirdplace.TXT");
    in__ >> score[2];
    in__.close();

    ifstream in___("resources/Fourthplace.TXT");
    in___ >> score[3];
    in___.close();

    sort(score, score + 4);

    ofstream out;
    out.open("resources/Firstplace.TXT");
    if (out.is_open())
    {
        out << score[3];
    }
    out.close();

    ofstream out_;
    out_.open("resources/Secondplace.TXT");
    if (out_.is_open())
    {
        out_ << score[2];
    }
    out_.close();
    
    ofstream out__;
    out__.open("resources/Thirdplace.TXT");
    if (out__.is_open())
    {
        out__ << score[1];
    }
    out__.close();

    
    ofstream out___;
    out___.open("resources/Fourthplace.TXT");
    if (out___.is_open())
    {
        out___ << clear;
    }
    out___.close();

    return 0;
}
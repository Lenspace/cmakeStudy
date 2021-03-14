#include <iostream>
using namespace std;
#include "globalFunc.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

int main()
{
    cout << "hello world." << endl;
    cout << "12 + 22 = " << add(12, 22) << endl;

    const char* json = "{\"project\" : \"rapidJson\", \"stars\" : 10}";
    Document d;
    d.Parse(json);

    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    Value& pro = d["project"];
    cout << pro.GetString() << endl;
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    cout << buffer.GetString() << endl;

    return 0;
}
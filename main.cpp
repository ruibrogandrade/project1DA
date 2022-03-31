#include <iostream>
#include "Application.h"

int main() {
    Application app;
    app.fileReaderPackages();
    app.fileReaderTransport();
    cout << app.getPackage().size() << endl;
    cout << app.getTransport().size();
    return 0;
}

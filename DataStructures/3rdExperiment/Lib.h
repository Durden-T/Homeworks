#define EXIT "!exit"

#define MAXSPILT 10
void splitToLine(ifstream &file, vector<string> &source);

void textQuery(vector<string> &source, const string &pattern);

int BM(const string &s, const string &p, int *bc, int *gs, int lineNumber);

void printResults(vector<int> &result, vector<string> &source);

int *getBc(const string &p);
int *getGs(const string &p);
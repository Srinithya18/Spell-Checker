#include <iostream>
#include <vector>
using namespace std;

class TrieNode
{
public:
    char data;
    TrieNode **children;
    bool isTerminal;
    string word;
    TrieNode(char data)
    {
        this->data = data;
        isTerminal = false;
        children = new TrieNode *[26];
        for (int i = 0; i < 26; i++)
        {
            children[i] = NULL;
        }
        word = "";
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode('\0');
    }
    void insert(string word)
    {
        TrieNode *curr = root;
        int index, i = 0;
        while (word[i])
        {
            index = word[i] - 'a';
            if (curr->children[index] == NULL)
            {
                curr->children[index] = new TrieNode(word[i]);
            }
            curr = curr->children[index];
            i += 1;
        }
        curr->isTerminal = true;
        curr->word = word;
    }

    bool search(TrieNode *root, string word)
    {
        if (word.size() == 0)
        {
            return root->isTerminal;
        }
        int index = word[0] - 'a';
        if (root->children[index] != NULL && root->children[index]->data == word[0])
        {
            return search(root->children[index], word.substr(1));
        }
        return false;
    }

    TrieNode *getPatternEndNode(TrieNode *root, string pattern)
    {
        if (pattern == "")
            return root;
        int index = pattern[0] - 'a';
        if (root->children[index])
            return getPatternEndNode(root->children[index], pattern.substr(1));
        return NULL;
    }

    void autoCompleteHelper(TrieNode *root, string pattern, string output, vector<string> &ans)
    {
        if (root == NULL)
            return;
        output = output + root->data;
        if (root->isTerminal)
        {
            // cout << pattern + output << endl;
            ans.push_back(pattern + output);
        }
        for (int i = 0; i < 26; i++)
        {
            autoCompleteHelper(root->children[i], pattern, output, ans);
        }
    }

    void autoComplete(string pattern)
    {

        vector<string> ans;
        TrieNode *rt = getPatternEndNode(root, pattern);
        if (rt == NULL)
        {
            cout << "0\nNo matches found\n";
            return;
        }
        if (search(root, pattern))
        {
            // cout << pattern << endl;
            ans.push_back(pattern);
        }
        for (int i = 0; i < 26; i++)
        {
            if (rt->children[i])
            {
                autoCompleteHelper(rt->children[i], pattern, "", ans);
            }
        }

        cout << ans.size() << '\n';
        if (ans.size() > 0)
        {

            for (auto &x : ans)
            {

                cout << x << " ";
            }
            cout << '\n';
        }
        else
        {
            cout << "No matches found" << '\n';
        }
    }

    void searchRecursive(TrieNode *node, char ch, const string &word, vector<int> &prevRow, int maxCost, vector<string> &results)
    {
        int size = prevRow.size();
        int minRow = 56;

        vector<int> currentRow(size);
        currentRow[0] = prevRow[0] + 1;
        int insertOrDel, replace;
        for (int i = 1; i < size; i++)
        {
            insertOrDel = min(currentRow[i - 1] + 1, prevRow[i] + 1);
            replace = (word[i - 1] == ch) ? prevRow[i - 1] : (prevRow[i - 1] + 1);
            currentRow[i] = min(insertOrDel, replace);
        }

        if ((currentRow[size - 1] <= maxCost) && (node->isTerminal))
        {
            results.push_back(node->word);
        }

        for (auto &it : currentRow)
        {
            if (it < minRow)
            {
                minRow = it;
            }
        }
        if (minRow <= maxCost)
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->children[i])
                {
                    searchRecursive(node->children[i], 'a' + i, word, currentRow, maxCost, results);
                }
            }
        }
    }

    void searchMatch(string word, int maxCost)
    {
        vector<string> results;
        int length = word.size();
        vector<int> currentRow(length + 1);
        for (int i = 0; i <= length; i++)
        {
            currentRow[i] = i;
        }
        for (int i = 0; i < 26; i++)
        {
            if (root->children[i])
            {
                searchRecursive(root->children[i], 'a' + i, word, currentRow, maxCost, results);
            }
        }
        cout << results.size() << endl;
        if (results.size())
        {

            for (auto &x : results)
                cout << x << " ";
            cout << '\n';
        }
        else
        {
            cout << "No similarities found with LD < 3" << '\n';
        }
    }
};

int main()
{
    Trie t;
    // t.insert("maneeshaaaaa");
    // t.insert("apple");
    // t.insert("applelap");
    // t.insert("maneesha");
    // t.insert("maneeshu");
    // t.insert("maneesh");
    // t.insert("manish");
    // t.insert("maneesha");
    // t.insert("mahesh");
    // t.insert("manoj");
    // t.insert("murthy");
    // t.insert("ravi");
    // t.insert("ravite");
    // t.insert("hello");
    // t.autoComplete( "maneesh");
    // t.autoComplete( "qu");
    // cout << t.search(t.root, "man") << endl;

    int n, q, c;
    string s;
    cin >> n;
    while (n--)
    {
        // getline(cin, s);
        cin >> s;
        t.insert(s);
    }
    cin >> q;
    while (q--)
    {
        cin >> c >> s;
        if (c == 1)
        {
            cout << t.search(t.root, s) << '\n';
        }
        else if (c == 2)
        {
            t.autoComplete(s);
        }
        else if (c == 3)
        {
            t.searchMatch(s, 3);
        }
    }

}
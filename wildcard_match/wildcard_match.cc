bool wildCardHelper(
    const string& s,
    const string& p,
    int iS,
    int iP,
    map<pair<int, int>, bool>& Memo,
    const vector<int>& suffixLen)
{
    // if both string and pattern ended, we have a match!
    if ((iS == s.length()) && (iP == p.length())) return true;

    // pattern empty, string is not empty
    if (iP == p.length()) return false;

    // string is empty, next pattern is not *
    if ((iS == s.length()) && p[iP] != '*') return false;

    // we have more non-* charcters to match than string length
    if ((s.length() - iS) < suffixLen[iP]) return false;
    
    // current pair of indices    
    pair<int, int> curPair = make_pair(iS, iP);

    // return if the result is memoized
    if (Memo.find(curPair) != Memo.end()) return Memo[curPair];

    // s has ended. We know next character in p is '*'. 
    // Lets check other following chars in p
    if (s.length() == iS) {
        return Memo[curPair] = wildCardHelper(s, p, iS, iP + 1, Memo, suffixLen);
    }

    // characters match when pattern is not '*'
    if ((s[iS] == p[iP]) || (p[iP] == '?')) {
        return Memo[curPair] = wildCardHelper(s, p, iS + 1, iP + 1, Memo, suffixLen);
    }

    // If pattern is '*', then explore both possibilities
    if (p[iP] == '*') {
        return Memo[curPair] =
            wildCardHelper(s, p, iS + 1, iP, Memo, suffixLen) ||
            wildCardHelper(s, p, iS, iP + 1, Memo, suffixLen);
    }
    
    return Memo[curPair] = false;
}

bool isWildCardMatch(const string& s, const string& p) {
    if (s.empty() && p.empty()) return true;

    map<pair<int, int>, bool> Memo;
    vector<int> suffixLen(p.length());

    // fill the suffix len with non-star chars so that
    // we know how many non-* chars after each index
    int cnt = 0;
    for (int iP = p.length() - 1; iP >= 0; --iP) {
        if (p[iP] != '*') ++cnt;
        suffixLen[iP] = cnt;
    }

    return wildCardHelper(s, p, 0, 0, Memo, suffixLen);
}
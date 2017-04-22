// Longest increasing sub-sequence 
// dynamic programming 
void LIS(const vector<int>& D, vector<int>& R)
{
    vector<vector<int>> L(D.size());
    unsigned max = 1; //first index
    unsigned index = 0;
    
    //Add first element to matrix
    L[0].push_back(D[0]);
    

    for (unsigned i = 1; i < D.size(); ++i)
    {
        for (unsigned j = 0; j < i; ++j)
        {
            if ((D[j] < D[i]) && L[i].size() < (L[j].size() + 1))
            {
                L[i] = L[j];
            }
        }
        L[i].push_back(D[i]);

        if (L[i].size() > max)
        {
            max = L[i].size();
            index = i;
        }
    }

    R = L[index];
}


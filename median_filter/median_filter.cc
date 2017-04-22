class MedianFilter
{
    const int WINDOW_SIZE       = 3; //Assume to be odd
    const int WINDOW_HALF_SIZE  = WINDOW_SIZE / 2;
    const int WINDOW_MID_VAL    = ((WINDOW_SIZE * WINDOW_SIZE) + 1) / 2;
    const int MAX_PIXEL_VALUE   = 256;

    vector<UCHAR> _medianValues;

private:
    UCHAR getMedian() const
    {
        int sum = 0;
        for (int i = 0; i < MAX_PIXEL_VALUE; ++i) {
            sum += _medianValues[i];
            if (sum >= WINDOW_MID_VAL) {
                return i;
            }
        }

        return 0;
    }

    void initializeMedian(
        const vector<vector<UCHAR>>& input,
        int rows,
        int cols) 
    {
        // we'll start from left corner. Number of zeros to pad
        int paddingZeros = WINDOW_SIZE + WINDOW_SIZE - 1;
        _medianValues[0] = paddingZeros;

        for (int row = 0; row <= WINDOW_HALF_SIZE; ++row) {
            for (int col = 0; col <= WINDOW_HALF_SIZE; ++col) {
                UCHAR index = 0;
                if (row < rows && col < cols) {
                    index = input[row][col];;
                }
                ++_medianValues[index];
            }
        }
    }

    void updateRow(
        const vector<vector<UCHAR>>& input,
        int rows,
        int cols,
        int curRow,
        bool leftToRight)
    {
        // remove entries from previous row
        int prevRow = curRow - WINDOW_HALF_SIZE - 1;
        int nextRow = curRow + WINDOW_HALF_SIZE;

        int startCol = leftToRight 
                        ? (0 - WINDOW_HALF_SIZE) 
                            : (cols - WINDOW_HALF_SIZE - 1);

        int endCol = leftToRight 
                        ? (0 + WINDOW_HALF_SIZE) 
                        : (cols + WINDOW_HALF_SIZE - 1);

        if (prevRow < 0) {
            _medianValues[0] -= WINDOW_SIZE;
        }
        else {
            for (int col = startCol; col <= endCol; ++col) {
                int index = 0;
                if (col >= 0 && col < cols) {
                    index = input[prevRow][col];
                }
                --_medianValues[index];
            }
        }

        // Add next row values
        if (nextRow >= rows) {
            _medianValues[0] += WINDOW_SIZE;
        }
        else {
            for (int col = startCol; col <= endCol; ++col) {
                int index = 0;
                if (col >= 0 && col < cols) {
                    index = input[nextRow][col];
                }
                ++_medianValues[index];
            }
        }
    }

    void updateCol(
        const vector<vector<UCHAR>>& input,
        int rows,
        int cols,
        int curRow,
        int curCol,
        bool leftToRight)
    {
        int prevCol = (leftToRight) ?
            (curCol - WINDOW_HALF_SIZE - 1) :
            (curCol + WINDOW_HALF_SIZE + 1);

        int startRow = curRow - WINDOW_HALF_SIZE;
        int endRow = curRow + WINDOW_HALF_SIZE;
        
        // remove prev col values
        if (prevCol < 0 || prevCol >= cols) {
            _medianValues[0] -= WINDOW_SIZE;
        }
        else {
            for (int row = startRow; row <= endRow; ++row) {
                int index = 0;
                if (row >= 0 && row < rows) {
                    index = input[row][prevCol];
                }
                --_medianValues[index];
            }
        }
        
        // add next col values
        int nextCol = (leftToRight) ?
            (curCol + WINDOW_HALF_SIZE) :
            (curCol - WINDOW_HALF_SIZE);

        // remove prev col values
        if (nextCol < 0 || nextCol >= cols) {
            _medianValues[0] += WINDOW_SIZE;
        }
        else {
            for (int row = startRow; row <= endRow; ++row) {
                int index = 0;
                if (row >= 0 && row < rows) {
                    index = input[row][nextCol];
                }
                ++_medianValues[index];
            }
        }
    }

public:
    MedianFilter()
        : _medianValues(MAX_PIXEL_VALUE) 
    {}

    vector<vector<UCHAR>> filter(const vector<vector<UCHAR>>& input)
    {
        if (input.empty() || input[0].empty()) return vector<vector<UCHAR>>();

        int rows = input.size();
        int cols = input[0].size();

        initializeMedian(input, rows, cols);

        vector<vector<UCHAR>> output(rows, vector<UCHAR>(cols, 0));
        bool leftToRight = true;

        for (int row = 0; row < rows; ++row) {
            if (row > 0) {
                updateRow(input, rows, cols, row, leftToRight);
            }
            for (int col = 0; col < cols; ++col) {
                int curCol = leftToRight ? col : (cols - col - 1);

                if (col > 0) {
                    updateCol(input, rows, cols, row, curCol, leftToRight);
                }
                
                UCHAR val = getMedian();       
                output[row][curCol] = val;
            }

            leftToRight = !leftToRight;
        }
        return output;
    }
};


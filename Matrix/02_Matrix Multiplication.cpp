vector<vector<int>> multiply(vector<vector<int>> &mat1, vector<vector<int>> &mat2) {
    
    int r1 = mat1.size(), c1 = mat1[0].size(); 
    int r2 = mat2.size(), c2 = mat2[0].size();        
    
    // only possible if c1 == r2

    vector<vector<int>> res(r1, vector<int>(c2, 0));

    
    for (int i = 0; i < r1; i++) { // Loop through each row of mat1

        for (int j = 0; j < c2; j++) {  // Loop through each column of mat2
            
            for (int k = 0; k < c1; k++) {

                res[i][j] += mat1[i][k] * mat2[k][j];
            
            }
        }
    }

    return res;
}
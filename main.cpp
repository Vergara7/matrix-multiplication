#include <iostream>
#include <vector>

using namespace std;

typedef std::uint32_t uint;

istream& operator >> (istream& in, vector<vector<uint>>& matrix){
	for (auto& row : matrix){
		for (uint& x : row)
			cin >> x;
	}
	return in;
}

vector<vector<uint>> multiply(vector<vector<uint>> left_matrix, vector<vector<uint>> right_matrix){
	assert(left_matrix[0].size() == right_matrix.size());
	size_t n = left_matrix.size(), m = right_matrix.size(), k = right_matrix[0].size();
	const size_t bits_in_uint = 32;
	size_t block_count = (m + bits_in_uint - 1) / bits_in_uint;
	vector<vector<uint>> compressed_left_matrix(n, vector<uint> (block_count));
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < block_count; j++){
			for (size_t l = 0; l < bits_in_uint; l++){
				size_t pos = l + bits_in_uint * j; 
				if (pos < m && left_matrix[i][pos])
					compressed_left_matrix[i][j] |= (1 << l);
			}
		}
	}
	vector<vector<uint>> compressed_right_matrix(k, vector<uint> (block_count));
	for (size_t i = 0; i < k; i++){
		for (size_t j = 0; j < block_count; j++){
			for (size_t l = 0; l < bits_in_uint; l++){
				size_t pos = l + bits_in_uint * j; 
				if (pos < m && right_matrix[pos][i])
					compressed_right_matrix[i][j] |= (1 << l);
			}
		}
	}
	vector<vector<uint>> result(n, vector<uint> (k));
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < k; j++){
			for (size_t t = 0; t < block_count; t++){
				if (compressed_left_matrix[i][t] & compressed_right_matrix[j][t]){
					result[i][j] = 1;
					break;
				}
			}
		}
	}
	return result;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	size_t n, m, k;
	cin >> n >> m >> k;
	vector<vector<uint>> left_matrix(n, vector<uint> (m));
	vector<vector<uint>> right_matrix(m, vector<uint>(k));
	cin >> left_matrix >> right_matrix;
	auto res = multiply(left_matrix, right_matrix);
	for (auto& row : res){
		for (uint x : row)
			cout << x << ' ';
		cout << '\n';
	}
	cerr << "DONE!" << endl;
	return 0;
}

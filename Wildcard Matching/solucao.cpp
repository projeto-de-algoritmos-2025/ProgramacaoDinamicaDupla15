class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size();
        int m = p.size();

        // dp[i][j] = será verdadeiro se a string s casar completamente com a string p
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        // ------------------------------
        // Caso base: string vazia x padrão vazio
        // ------------------------------
        dp[0][0] = true;

        // ------------------------------
        // Caso base: s = "" e p = "***..."
        // Isso corresponde a inserir GAPs em Y repetidas vezes,
        // porque '*' pode consumir zero caracteres de s.
        // ------------------------------
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') {
                // GAP EM Y: '*' consome vazio em s, então dp[0][j] depende de dp[0][j-1]
                dp[0][j] = dp[0][j - 1];
            }
        }

        // -------------------------------------------------------
        // Preenchimento da tabela de alinhamento
        // -------------------------------------------------------
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {

                // Caso 1: MATCH ou MISMATCH controlados por '?' ou igualdade
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    // MATCH: caractere casa diretamente
                    // MISMATCH: '?' permite casar qualquer caractere
                    // Alinhamento: dp[i][j] = dp[i-1][j-1]
                    dp[i][j] = dp[i - 1][j - 1];
                }

                // Caso 2: '*' → pode ser GAP em X ou GAP em Y
                else if (p[j - 1] == '*') {

                    // GAP EM X:
                    // '*' consome UM caractere de s
                    // então avançamos i (string) e permanecemos em j (padrão)
                    // Alinhamento: dp[i][j] |= dp[i-1][j]
                    bool gapX = dp[i - 1][j];

                    // GAP EM Y:
                    // '*' consome ZERO caracteres de s
                    // avançamos j (padrão)
                    // Alinhamento: dp[i][j] |= dp[i][j-1]
                    bool gapY = dp[i][j - 1];

                    dp[i][j] = gapX || gapY;
                }

                // Caso 3: MISMATCH real
                else {
                    // Não faz nada: dp[i][j] permanece falso
                    // Esse é um mismatch sem '?', impossível casar
                }
            }
        }

        return dp[n][m];
    }
};

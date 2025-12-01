from typing import List
from bisect import bisect_left

class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        # Ordena pelo tempo de fim para processar na ordem cronológica correta
        events.sort(key=lambda x: x[1])
        
        n = len(events)
        
        # dp[i][j]: max valor considerando até o evento 'i' com 'j' escolhas
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        # Lista auxiliar apenas com os 'ends' para a busca binária
        end_times = [e[1] for e in events]
        
        for i in range(1, n + 1):
            start, end, value = events[i-1]
            
            # encontra o índice do evento anterior que NÃO conflita
            # (que terminou antes do 'start' atual)
            idx = bisect_left(end_times, start)
            
            for j in range(1, k + 1):
                # Opção 1: Não incluir o evento atual (mantém o valor anterior)
                not_take = dp[i-1][j]
                
                # Opção 2: Incluir o evento atual (valor + resultado do índice compatível)
                take = value + dp[idx][j-1]
                
                dp[i][j] = max(not_take, take)
                
        return dp[n][k]
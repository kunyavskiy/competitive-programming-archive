fun main() {
    while (true) {
        val (n, m) = (readlnOrNull() ?: break).split(" ").map { it.toInt() }
        val a = readInts()

        val dp = List(n + 1) { DoubleArray(n + 1) }
        dp[0][n] = 1.0

        for (i in 1 until dp.size) {
            var s = 0.0
            for (j in n - 1 downTo 0) {
                s += dp[i - 1][j + 1]
                dp[i][j] = s / (n - j)
            }
        }

        val dp2 = List(n + 1) { DoubleArray(n + 1) }
        dp2[0][n] = 1.0
        for (i in 1 until dp.size) {
            for (j in n - 1 downTo 0) {
                dp2[i][j] = dp2[i - 1][j] + dp[i][j]
            }
        }


        //println(dp.map { it.toList() })

        val ans = DoubleArray(m)
        for (i in 1 until dp.size) {
            for ((index, v) in a.withIndex()) {
                var c = 1.0
                for (j in 0 until m) {
                    if (j != index) {
                        c *= 1.0 - dp2[i - 1][a[j]]
                    }
                }
                ans[index] += dp[i][v] * c
            }
        }
        println(ans.joinToString(" ") { "%.10f".format(it) })
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
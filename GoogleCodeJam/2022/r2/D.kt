private fun solve(c:Int, x: LongArray, s:IntArray) : Long {
    val dp = LongArray(x.size + 1)
    val lastSum = Array(2) { LongArray(2 * x.size + 1) { 0 } }
    val last = IntArray(2 * x.size + 1) { 0 }
    var curBal = x.size
    var sum0 = 0L
    var sum1 = 0L
    lastSum[0][curBal] = 0
    lastSum[1][curBal] = 0
    last[curBal] = 0
    for (i in x.indices) {
        dp[i + 1] = dp[i] + x[i] * 2
        if (i >= 1) {
            dp[i + 1] = minOf(dp[i + 1], dp[i - 1] + x[i] * 2 + if (s[i] != s[i - 1]) 0 else c)
        }
        if (s[i] == 0) {
            sum0 += 2 * x[i]
            curBal++
        } else {
            sum1 += 2 * x[i]
            curBal--
        };
        if (last[curBal] != -1) {
            dp[i + 1] = minOf(dp[i + 1], dp[last[curBal]] + if (s[i] == 0) sum0 - lastSum[0][curBal] else sum1 - lastSum[1][curBal])
        }
        last[curBal] = i + 1
        lastSum[0][curBal] = sum0
        lastSum[1][curBal] = sum1
    }
    return dp.last()
}

private fun solve() {
    val (n, c) = readInts()
    val (tempp, tempn) = List(n) { readInts() }.sortedBy { it[0] }.partition { it[0] > 0 }
    val ans1 = solve(c, tempp.map { it[0].toLong() }.toLongArray(), tempp.map { it[1] }.toIntArray())
    val ans2 = solve(c, tempn.map { -it[0].toLong() }.reversed().toLongArray(), tempn.reversed().map { it[1] }.toIntArray())
    println(ans1 + ans2)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
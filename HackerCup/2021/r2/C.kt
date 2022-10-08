private fun solve(s: Array<String>, r: Int) : Int {
    val n = s.size
    val m = s[0].length
    val cnt = IntArray(m) { col -> (r + 1 until n).count { s[it][col] == 'X' } }
    val ans = (r downTo 0).minOfOrNull { row ->
        for (c in 0 until m) {
            if (s[row][c] == 'X') {
                cnt[c]++
            }
        }
        (r - row) + (0 until m).count { s[row][it] == 'X' || cnt[it] >= n - r }
    }!!
    return minOf(ans, r + 1 + (0 until m).count { cnt[it] >= n - r })
}

private fun solve() {
    val (n, m, k_) = readInts()
    val k = k_ - 1
    val s = Array(n) { readLn() }
    val ans1 = solve(s, k)
    val ans2 = solve(s.reversed().toTypedArray(), n - k - 1)
    println(minOf(ans1, ans2))
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
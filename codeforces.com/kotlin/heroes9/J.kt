import kotlin.math.abs

fun main() {
    val n = readInt()
    val c = readInts()
    val g = List(n) { mutableListOf<Pair<Int, Int>>() }
    repeat(n - 1) {
        val (a, b, w) = readInts()
        g[a - 1].add(b - 1 to w)
        g[b - 1].add(a - 1 to w)
    }
    val size = List(2) { IntArray(n) }
    var ans = 0L
    fun dfs(v: Int, p: Int) {
        size[c[v]][v] = 1
        for ((u, w) in g[v]) {
            if (u != p) {
                dfs(u, v)
                size[0][v] += size[0][u]
                size[1][v] += size[1][u]
                ans += abs(size[0][u] - size[1][u]) * w.toLong()
            }
        }
    }
    dfs(0, 0)
    println(ans)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
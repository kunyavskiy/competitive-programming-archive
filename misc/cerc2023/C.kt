fun main() {
    val (_, C, T) = readInts()
    val c = readInts()
    val g = readInts()
    val t = readInts()
    val profit = List(C) { i ->
        val s = readInts()
        c[i] - s.zip(g).sumOf { it.first.toLong() * it.second }
    }
    val flow = List(C + T + 2) { IntArray(C + T + 2) }
    var ans = 0L
    for (i in c.indices) {
        val tools = readInts().map { it - 1 }.drop(1)
        for (j in tools) {
            flow[i][j + C] = Int.MAX_VALUE / 2
        }
        if (profit[i] > 0) {
            flow[C + T][i] = profit[i].toInt()
            ans += profit[i]
        }
    }
    for (i in t.indices) {
        flow[C + i][C + T + 1] = t[i]
    }
    val used = BooleanArray(flow.size)
    fun dfs(v: Int, cur:Int, lim:Int): Int {
        if (v == flow.lastIndex) return cur
        used[v] = true
        for (i in flow[v].indices) {
            if (!used[i] && flow[v][i] >= lim) {
                val r = dfs(i, minOf(cur, flow[v][i]), lim)
                if (r > 0) {
                    flow[v][i] -= r
                    flow[i][v] += r
                    return r
                }
            }
        }
        return 0
    }
    for (lim in 30 downTo 0) {
        while (true) {
            val x = dfs(C + T, Int.MAX_VALUE, 1 shl lim)
            used.fill(false)
            if (x == 0) break
            ans -= x.toLong()
        }
    }
    println(ans)
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
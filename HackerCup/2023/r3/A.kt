private fun can(a: List<Int>, count: Int) : Boolean {
    if (a.sum() % count != 0) return false
    if (a.size < count) return false
    val each = a.sum() / count
    val cache = hashSetOf<List<Int>>()
    fun go(position: Int, cur: IntArray) : Boolean {
        if (position == a.size) return true
        if (!cache.add(cur.sorted())) return false
        for (i in cur.indices) {
            if (cur[i] >= a[position]) {
                cur[i] -= a[position]
                if (go(position + 1, cur)) return true
                cur[i] += a[position]
            }
        }
        return false
    }
    return go(0, IntArray(count) { each })
}

private fun solve() {
    val (n, m) = readInts()
    val g = List(n) { mutableListOf<Int>() }
    repeat(m) {
        val (a, b) = readInts().map { it - 1 }
        g[a].add(b)
        g[b].add(a)
    }
    val color = IntArray(n) { -1 }
    fun dfs(v: Int, c: Int) {
        if (color[v] != -1) return
        color[v] = c
        g[v].forEach { dfs(it, c) }
    }
    for (i in 0 until n) {
        dfs(i, i)
    }
    val counts = color.toList().groupingBy { it }.eachCount().values.sortedDescending()
    println((1..n).filter { can(counts, it) }.joinToString(" "))
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
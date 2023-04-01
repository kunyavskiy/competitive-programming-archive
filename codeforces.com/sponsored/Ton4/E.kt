private class DSU(n: Int) {
    val p = IntArray(n) { it }
    val size = IntArray(n) { 1 }
    val can = BooleanArray(n) { false }
    fun get(x: Int) : Int = when {
        p[x] == x -> x
        else -> get(p[x]).also { p[x] = it }
    }
    fun join(a:Int, b: Int) {
        val aa = get(a)
        val bb = get(b)
        if (aa == bb) return
        if (size[aa] < size[bb]) {
            p[aa] = bb
            size[bb] += size[aa]
        } else {
            p[bb] = aa
            size[aa] += size[bb]
        }
    }
}

private fun solve() {
    val (n, m) = readInts()
    val g = List(n) { mutableListOf<Int>() }
    val w = readInts()
    repeat(m) {
        val (a, b) = readInts().map { it - 1 }
        g[a].add(b)
        g[b].add(a)
    }
    val d = DSU(n)
    val done = BooleanArray(n)
    for (v in (0 until n).sortedBy { w[it] }) {
        done[v] = true
        val good = w[v] == 0 || g[v].any { d.can[d.get(it)] && d.size[d.get(it)] >= w[v] }
        for (u in g[v]) {
            if (done[u]) {
                d.join(u, v)
            }
        }
        d.can[d.get(v)] = good
    }
    if (d.size[d.get(0)] == n && d.can[d.get(0)]) {
        println("YES")
    } else {
        println("NO")
    }
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
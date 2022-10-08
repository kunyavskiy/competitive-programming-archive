class DSU(n: Int, val h: IntArray) {
    val p = IntArray(n) { it }
    val size = IntArray(n) { 1 }
    val highest = IntArray(n) { it }

    operator fun get(v: Int) : Int {
        return if (p[v] == v) {
            v
        } else {
            val t = get(p[v])
            p[v] = t
            t
        }
    }

    fun join(u: Int, v: Int) {
        val uu = get(u)
        val vv = get(v)
        if (uu != vv) {
            val j = if (size[uu] > size[vv]) uu else vv
            val other = uu + vv - j
            p[other] = j
            size[j] += size[other]
            highest[j] = if (h[highest[j]] < h[highest[other]]) highest[j] else highest[other]
        }
    }

    fun getHigh(v: Int) = highest[get(v)]
}

private fun solve() {
    val n = readInt()
    val g = Array(n) { mutableListOf<Int>() }
    repeat(n - 1) {
        val (a, b) = readInts().map { it - 1 }
        g[a].add(b)
        g[b].add(a)
    }
    val queue = mutableListOf(0)
    val h = IntArray(n) { -1 }
    val p = IntArray(n) { -1 }
    h[0] = 0
    for (pos in 0 until n) {
        val v = queue[pos]
        for (u in g[v]) {
            if (h[u] == -1) {
                h[u] = h[v] + 1
                queue.add(u)
                p[u] = v
            }
        }
    }
    val c = readInts()
    val d = DSU(n, h)

    (0 until n).groupBy { c[it] }.values.forEach {
        it.zipWithNext().forEach { (u, v) ->
            while (d[u] != d[v]) {
                val a = d.getHigh(u)
                val b = d.getHigh(v)
                if (h[a] > h[b]) {
                    d.join(a, p[a])
                } else {
                    d.join(b, p[b])
                }
            }
        }
    }
    val components = (0 until n).groupBy { d[it] }.count()
    println(components - 1)
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
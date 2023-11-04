private fun solve() {
    val n = readInt()
    val p = listOf(-1) + readInts().map { it - 1 }
    val g = List(n) { mutableListOf<Int>() }
    for (i in 1 until n) {
        g[p[i]].add(i)
    }
    val depth = IntArray(n) { 1 }
    val secondDepth = IntArray(n) { 1 }
    val dfs = DeepRecursiveFunction { v: Int ->
        for (u in g[v]) {
            callRecursive(u)
            var x = depth[u] + 1
            if (x > depth[v]) {
                val t = depth[v]
                depth[v] = x
                x = t
            }
            if (x > secondDepth[v]) {
                secondDepth[v] = x
            }
        }
    }
    dfs(0)
    for (i in 0 until n) {
        g[i].sortByDescending { depth[it] }
    }
    val upDepth = IntArray(n) { 0 }
    val dfs2 = DeepRecursiveFunction { v: Int ->
        if (p[v] != -1)
            upDepth[v] = maxOf(upDepth[p[v]] + 1, if (depth[p[v]] == depth[v] + 1) secondDepth[p[v]] else depth[p[v]])
        for (u in g[v]) {
            callRecursive(u)
        }
    }
    dfs2(0)
    fun number(p: Int, v: Int) : Long {
        val fromP = sequence {
            var added = false
            var removed = false
            for (i in g[p]) {
                if (!removed && depth[i] == depth[v]) {
                    removed = true
                } else {
                    if (!added && upDepth[p] > depth[i]) {
                        added = true
                        yield(upDepth[p])
                    }
                    yield(depth[i])
                }
            }
            if (!added) {
                yield(upDepth[p])
            }
        }
        val fromV = g[v].asSequence().map { depth[it] }
        val ans = fromV.zip(fromP) { a, b -> minOf(a, b) }.sumOf { it.toLong() }
        return ans
    }

    println((0 until n).sumOf { v -> g[v].sumOf { number(v, it) } })
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
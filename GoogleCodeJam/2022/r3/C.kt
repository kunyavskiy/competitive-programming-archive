import java.util.TreeSet

private fun solve() {
    val n = readInt()
    val l = readInts().map { it - 1 }.toIntArray()
    val r = readInts().map { it - 1 }.toIntArray()
    val gb = List(n) { mutableListOf<Int>() }
    fun add(i: Int, j: Int) {
        gb[i].add(j)
        gb[j].add(i)
    }
    for (i in 0 until n) {
        add(i, l[i])
        add(i, l[l[i]])
        add(i, r[l[i]])
        add(i, r[i])
        add(i, l[r[i]])
        add(i, r[r[i]])
    }
    val g = gb.map { it.distinct().toIntArray() }
    if (g.indices.any { g[it].contains(it) }) {
        println("IMPOSSIBLE")
        return
    }
    val d = IntArray(n) { g[it].size }
    val s = sortedSetOf<Pair<Int, Int>>(compareBy({ it.first }, { it.second }))
    for (i in d.indices) {
        s.add(d[i] to i)
    }
    val done = BooleanArray(n) { false }
    val order = buildList {
        while (!s.isEmpty()) {
            val (_, v) = s.first()
            s.remove(d[v] to v)
            add(v)
            done[v] = true
            for (u in g[v]) {
                if (!done[u]) {
                    s.remove(d[u] to u)
                    d[u] -= 1
                    s.add(d[u] to u)
                }
            }
        }
        reverse()
    }
    val colors = IntArray(n) { -1 }
    for (v in order) {
        while (true) {
            colors[v]++
            if (g[v].none { colors[it] == colors[v] }) {
                break
            }
        }
    }
    println(colors.map { "ACDEHIJKMORST"[it] }.joinToString(""))
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
import kotlin.math.*

private data class Point(val x: Int, val y: Int, val id: Int) {
    fun dist(other: Point) = d(other.x - x, other.y - y)
    companion object {
        fun d(x: Int, y: Int) = x.toLong() * x + y.toLong() * y
    }
}

private fun go(a:List<Point>, b:List<Point>) : List<Pair<Int, Int>>? {
    if (a.isEmpty()) { return emptyList() }
    for (p in a) {
        val cls = b.minByOrNull { p.dist(it) }!!
        if (cls.id == 0) continue
        val subans = go(a.filterNot { it == p }, b.filterNot { it == cls })
        if (subans != null) {
            return listOf(p.id to cls.id) + subans
        }
    }
    return null
}

private fun solve() {
    val n = readInt()
    val a = List(n) { id -> readInts().let { Point(it[0], it[1], id) } }
    val b = List(n + 1) { id -> readInts().let { Point(it[0], it[1], id) } }.reversed()
    val ans = go(a, b)
    if (ans == null) {
        println("IMPOSSIBLE")
    } else {
        println("POSSIBLE")
        println(ans.joinToString("\n") { "${it.first + 1} ${it.second + 1}" })
    }
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
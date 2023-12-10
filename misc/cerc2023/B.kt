import kotlin.math.sqrt

fun main() {
    val n = readInt()
    val s = readln()
    val pts = List(n) { readInts() }
    val (b, g) = s.toCharArray().zip(pts).partition { it.first == 'B' }
    val ans = b.map { it.second }.total() + g.map { it.second }.total()
    println("%.10f".format(ans))
}

fun List<List<Int>>.total() : Double {
    val n = size
    val v = subList(0, n / 2).zip(subList(n / 2, n))
    return v.sumOf { (p1, p2) ->
        val (x1, y1) = p1
        val (x2, y2) = p2
        sqrt((x1 - x2).toDouble() * (x1 - x2) + (y1 - y2).toDouble() * (y1 - y2))
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
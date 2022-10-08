import kotlin.math.*

fun count(r: Int) : Int {
    return round(r * sqrt(2.0) - 1).toInt()
    val s = mutableSetOf<Long>()
    for (x in 1..r) {
        val y = round(sqrt((r * r - x * x).toDouble())).toInt()
        if (y != 0) {
            s.add(x * 1000000000L + y)
            s.add(y * 1000000000L + x)
        }
    }
    return s.size
}

private fun solve() {
    val R = readInt()
    var ans = 0L
    for (x in -R..R) {
        ans += 2 * floor( sqrt((R * R + R - x * x).toDouble())).toInt() + 1
    }
    ans -= 1
    for (r in 1..R) {
        ans -= 4 * (count(r) + 1)
    }
    println(ans)
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
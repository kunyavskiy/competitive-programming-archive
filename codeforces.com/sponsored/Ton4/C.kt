import java.util.StringTokenizer
import kotlin.time.*

private fun solve() {
    val (n, c, d) = readLongs()
    val x = StringTokenizer(readLn())
    val t = IntArray(n.toInt()) { x.nextToken().toInt() }
    t.sort()
    var index = 0
    var ans = n * c + d
    for (i in t.indices) {
        if (i == 0 || t[i] != t[i-1]) index++
        ans = minOf(ans, (n - index) * c + (t[i] - index) * d)
    }
    println(ans)
}

@OptIn(ExperimentalTime::class)
fun main() {
    //println(measureTime {
        repeat(readInt()) {
            solve()
        }
    //})
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
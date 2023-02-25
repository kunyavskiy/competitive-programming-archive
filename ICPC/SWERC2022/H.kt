import kotlin.math.*

fun main() {
    readInts()
    val s = readLn()
    val p = s.count { it == '+' }
    val m = s.count { it == '-' }
    repeat(readInt()) {
        val (a, b) = readLongs()
        val result = run {
            val bal = a * p - a * m
            val diff = (b - a)
            //println("bal = $bal, diff = $diff, p = $p, m = $m")
            when {
                diff == 0L -> bal == 0L
                diff.sign == bal.sign -> bal % diff == 0L && abs(bal / diff) <= m
                diff.sign != bal.sign -> bal % diff == 0L && abs(bal / diff) <= p
                else -> TODO()
            }
        }
        println(if (result) "YES" else "NO")
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
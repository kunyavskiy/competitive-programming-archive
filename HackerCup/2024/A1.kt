private val peaks = mutableListOf<Long>()
private fun solve() {
    val (a, b, m) = readLongs()
    println(peaks.count { it in a..b && it % m == 0L })
}

fun main() {
    for (k in 0..9) {
        for (t in (k+1)..9) {
             val s = ((t-k..t).toList() + (t-1 downTo t-k).toList()).joinToString("")
            peaks.add(s.toLong())
        }
    }
    //println(peaks)

    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
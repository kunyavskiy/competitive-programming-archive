import kotlin.math.*

fun no() = println("IMPOSSIBLE")

private fun solve() {
    readInt()
    val s = readStrings().toMutableList()
    outer@while (true) {
        s.sortByDescending { it.all { l -> l == it[0] } }
        for (i in s.indices) {
            for (j in s.indices) {
                if (i != j && s[i].last() == s[j].first()) {
                    s.add(s[i] + s[j])
                    s.removeAt(max(i, j))
                    s.removeAt(min(i, j))
                    continue@outer
                }
            }
        }
        break
    }
    val answer = s.joinToString("").takeIf { ans ->
        "!$ans".zipWithNext().filter { it.first != it.second }.map { it.second }.groupingBy { it }.eachCount().all { it.value == 1 }
    } ?: "IMPOSSIBLE"
    println(answer)
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
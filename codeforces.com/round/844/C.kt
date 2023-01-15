import kotlin.math.*

private fun solve() {
    readInt()
    val a = readLn().toCharArray()
    val cnt = IntArray(26)
    for (c in a) {
        cnt[c.code - 'a'.code]++
    }
    val cnts = cnt.mapIndexed { index, i ->
        i to ('a' + index)
    }.sortedBy { it.first }
    val res = (1..26).filter { a.size % it == 0 }.minBy {c ->
        cnts.dropLast(c).sumOf { it.first } + cnts.takeLast(c).sumOf { abs(it.first - a.size / c) }
    }
    val rcnts = (cnts.dropLast(res).map { it.second to 0 } + cnts.takeLast(res).map { it.second to (a.size / res) }).associate { it }.toMutableMap()
    val ans = CharArray(a.size) { '?' }
    for (i in a.indices) {
        if (rcnts[a[i]]!! > 0) {
            rcnts[a[i]] = rcnts[a[i]]!! - 1
            ans[i] = a[i]
        }
    }
    val rem = rcnts.flatMap { (k, v) -> List(v) { k } }
    var pt = 0
    for (i in ans.indices) {
        if (ans[i] == '?') {
            ans[i] = rem[pt++]
        }
    }

    println(ans.indices.count { ans[it] != a[it] })
    println(ans.joinToString(""))
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
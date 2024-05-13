import java.math.BigInteger

private fun solve() {
    val (n, hp) = readInts()
    val a = readInts()
    val m = readInt()
    val s = List(m) { readInts().drop(1).map { it - 1 } }
    val change = Array(n + m) { BigInteger.ZERO }
    val min = Array(n + m) { BigInteger.ZERO }
    for (i in 0 until n) {
        change[i] = a[i].toBigInteger()
        min[i] = minOf(BigInteger.ZERO, change[i])
    }
    for (i in 0 until m) {
        val (ch, mi) = s[i].fold(BigInteger.ZERO to BigInteger.ZERO) { (c, mi), id ->
            c + change[id] to minOf(mi, c + min[id])
        }
        change[n + i] = ch
        min[n + i] = mi
    }
    tailrec fun go(h: BigInteger, spell: Int) : Int {
        if ((h + min[spell]) > BigInteger.ZERO) return -1
        if (spell < n) return spell + 1
        var curh = h
        for (i in s[spell - n]) {
            if ((curh + min[i]) <= BigInteger.ZERO) return go(curh, i)
            curh += change[i]
        }
        error("unreachable")
    }
    println(go(hp.toBigInteger(), change.lastIndex))
}

fun main() {
    repeat(readInt()) {
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
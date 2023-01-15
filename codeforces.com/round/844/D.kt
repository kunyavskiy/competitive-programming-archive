import kotlin.math.*

fun Long.isSquare() : Boolean {
    var d = sqrt(toDouble()).toLong()
    while (d * d < this) d++
    while (d * d > this) d--
    return d * d == this
}

private fun solve() {
    val n = readInt()
    val v = readLongs().sorted().toLongArray()
    val cand = mutableListOf(0L)
    for (i in 0 until n) {
        for (j in i + 1 until n) {
            val diff = v[j] - v[i]
            var d = 1
            while (d * d <= diff) {
                if (diff % d == 0L) {
                    val `a+b` = (diff / d)
                    val `a-b` = d.toLong()
                    if (`a+b` % 2L == `a-b` % 2L) {
                        val a = (`a+b` + `a-b`) / 2
                        val b = (`a+b` - `a-b`) / 2
                        val a2 = a * a
                        val b2 = b * b
                        require(b2 - v[i] == a2 - v[j]) { "$a2, $b2, ${v[i]}, ${v[j]}" }
                        if (b2 - v[i] in 0L..1_000_000_000_000_000_000L) {
                            cand.add(b2 - v[i])
                        }
                    }
                }
                d++
            }
        }
    }
    val ans = max(1, cand.distinct().maxOf { x ->
        v.count { (it + x).isSquare() }
    })
    println(ans)
   // require(ans == (0..1000000L).maxOf { x ->
   //     v.count { (it + x).isSquare() }
    //})
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
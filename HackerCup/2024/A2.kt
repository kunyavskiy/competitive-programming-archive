private fun List<Long>.lowerBound(x: Long) = binarySearch(x).let { if (it < 0) it.inv() else it }

fun main() {
    val incs = buildList<List<Long>> l1@{
        add(emptyList<Long>())
        add((1L..9L).toList())
        for (i in 2..8) {
            add(buildList {
                for (j in this@l1.last()) {
                    for (t in j % 10 ..9) {
                        add(j * 10 + t)
                    }
                }
            })
        }
    }.flatten()
    val decs = incs.map { it.toString().reversed().toLong() }
    val pw10 = buildList<Long> {
        add(1L)
        for (i in 1..18) add(last() * 10L)
    }.toLongArray()
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        val (a, b, m) = readLongs()
        data class Key(val length: Int, val last: Int, val mod: Long)

        val dg = decs.groupBy {
            val x = it.toString()
            Key(x.length, x[0].digitToInt(), it % m)
        }
        var ans = 0
        for (i in 1..9) {
            if (i in a..b && i % m == 0L) ans++
        }
        for (i in incs) {
            val l = i.toString().length
            for (n in ((i % 10).toInt() + 1)..9) {
                val x = (i * 10 + n) * pw10[l]
                for (nn in 1 until n) {
                    val lst = dg[Key(l, nn, (m - x % m) % m)] ?: continue
                    ans += lst.lowerBound(b + 1 - x) - lst.lowerBound(a - x)
                }
            }
        }
        println(ans)
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
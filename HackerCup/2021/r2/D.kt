import kotlin.time.*

fun findSubset(values: List<Int>) : Pair<List<Int>, List<Int>>? {
    val prev = IntArray(values.sum() + 1) { -1 }
    prev[0] = -2
    fun restore(x: Int) : MutableList<Int> {
        val res = mutableListOf<Int>()
        var cx = x
        while (cx != 0) {
            res.add(prev[cx])
            cx -= values[prev[cx]]
        }
        return res
    }
    for ((index, v) in values.withIndex()) {
        for (i in prev.size - 1 downTo 0) {
            if (prev[i] != -1) {
                if (prev[i + v] != -1) {
                    val s1 = restore(i)
                    s1.add(index)
                    val s2 = restore(i + v)
                    return s1.filterNot { it in s2 } to s2.filterNot { it in s1 }
                } else {
                    prev[i + v] = index
                }
            }
        }
    }
    return null
}

private fun solve() {
    val (n, k) = readInts()
    val l = readInts()
    var x = mutableListOf<Int>()
    var pos = 0
    val ans1 = mutableListOf<Int>()
    val ans2 = mutableListOf<Int>()
    while (x.size + (n - pos) > k) {
        while (x.size < 24 && pos < n) {
            x.add(pos)
            pos += 1
        }
        val (s1, s2) = findSubset(x.map { l[it] }) ?: return println("Impossible")
        ans1.addAll(s1.map {x[it]})
        ans2.addAll(s2.map {x[it]})
        x = x.filterIndexed { index, _ -> index !in s1 && index !in s2 }.toMutableList()
    }
    println("Possible")
    println(ans1.joinToString(" ") { (it + 1).toString() })
    println(ans2.joinToString(" ") { (it + 1).toString() })
}

@OptIn(ExperimentalTime::class)
fun main() {
    val x = measureTime {
        repeat(readInt()) {
            print("Case #${it + 1}: ")
            solve()
        }
    }
    //System.err.println(x)
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
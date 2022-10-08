import kotlin.time.*

infix fun Int.edge(x: Int) = minOf(this, x) * 1239179L + maxOf(x, this)

fun <K> Map<K, Int>.getOrZero(key: K) = getOrDefault(key, 0)

private fun solve() {
    val (n, m, q) = readInts()
    val cap = mutableMapOf<Long, Int>()
    val gt = List(n) { mutableListOf<Int>() }
    repeat(m) {
        val (a, b, c) = readInts()
        gt[a - 1].add(b - 1)
        gt[b - 1].add(a - 1)
        cap[(a - 1) edge (b - 1)] = c
    }
    val g = gt.map { it.toIntArray() }

    val cache = mutableMapOf<Long, Long>()

    //var ops = 0L

    val answer = LongArray(q) {
        val (x, y) = readInts().map { it - 1 }
        cache.getOrPut(x edge y) {
            val smaller = if (g[x].size < g[y].size) x else y
            cap.getOrZero(x edge y).toLong() * 2 + g[smaller].sumOf {
                //ops += 1
                if (it == x || it == y)
                    0L
                else
                    minOf(
                        cap.getOrZero(x edge it),
                        cap.getOrZero(y edge it)
                    ).toLong()
            }
        }
    }
    //System.err.println(ops)
    println(answer.joinToString(" "))
}

@OptIn(ExperimentalTime::class)
fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        val time = measureTime {
            solve()
        }
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
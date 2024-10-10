fun main() {
    val n = 10_000_000
    val p = BooleanArray(n + 1) { false }
    val primes = mutableListOf<Int>()
    for (i in 2..n) {
        if (!p[i]) {
            primes.add(i)
            for (j in 2 * i ..n step i) {
                p[j] = true
            }
        }
    }
    val ans = IntArray(n + 1) { 0 }
    for (i in primes) {
        for (j in primes.take(2)) {
            if (i + j > n) break
            if (!p[i + j]) {
                //println("$i = ${i + j} - $j")
                ans[i + j]++
                break
            }
        }
    }
    for (i in 2..n) {
        ans[i] += ans[i-1]
    }

    repeat(readInt()) {
        println("Case #${it + 1}: ${ans[readInt()]}")
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
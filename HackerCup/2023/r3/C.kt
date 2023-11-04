private fun solve() {
    val (r, c) = readInts()
    val a = Array(r) { readLongs().toLongArray() }
    val toHere = Array(r) { LongArray(c) { 0L } }
    val fromHere = Array(r) { LongArray(c) { 0L } }
    toHere[0][0] = a[0][0]
    for (i in 0 until r) {
        for (j in 0 until c) {
            if (i != r - 1) toHere[i + 1][j] = maxOf(toHere[i + 1][j], toHere[i][j] + a[i + 1][j])
            if (j != c - 1) toHere[i][j + 1] = maxOf(toHere[i][j + 1], toHere[i][j] + a[i][j + 1])
        }
    }
    fromHere[r - 1][c - 1] = a[r - 1][c - 1]
    for (i in r - 1 downTo  0) {
        for (j in c - 1 downTo  0) {
            if (i != 0) fromHere[i - 1][j] = maxOf(fromHere[i - 1][j], fromHere[i][j] + a[i - 1][j])
            if (j != 0) fromHere[i][j - 1] = maxOf(fromHere[i][j - 1], fromHere[i][j] + a[i][j - 1])
        }
    }

    fun to(i: Int, j: Int) = toHere.getOrNull(i)?.getOrNull(j) ?: 0
    fun from(i: Int, j: Int) = fromHere.getOrNull(i)?.getOrNull(j) ?: 0

    fun check(lim: Long) : Boolean {
        val dpu = Array(r) { BooleanArray(c) { false } }
        val dpr = Array(r) { BooleanArray(c) { false } }
        dpu[r-1][0] = true
        dpr[r-1][0] = true
        for (i in r - 1 downTo 0) {
            for (j in 0 until c) {
                if (dpu[i][j]) {
                    var best = maxOf(to(i, j - 1), to(i - 1, j))
                    for (k in j+1 until c) {
                        if (best + from(i, k + 1) < lim) {
                            dpr[i][k] = true
                        }
                        best = maxOf(best, to(i - 1, k))
                        if (best + from(i + 1, k) >= lim) break
                    }
                }
                if (dpr[i][j]) {
                    var best = maxOf(from(i, j + 1), from(i + 1, j))
                    for (k in i-1 downTo 0) {
                        if (best + to(k - 1, j) < lim) {
                            dpu[k][j] = true
                        }
                        best = maxOf(best, from(k, j + 1))
                        if (best + to(k, j - 1) >= lim) break
                    }
                }
            }
        }
        return !dpu[0][c-1] && !dpr[0][c-1]
    }

    //require(check(5))

    var lf = 0L
    var rg = from(0, 0) + 1
    while (rg - lf > 1) {
        val mid = (lf + rg) / 2
        if (check(mid)) {
            lf = mid
        } else {
            rg = mid
        }
    }
    println(lf)
}

fun main() {
    repeat(readInt()) {
        print("Case #${it + 1}: ")
        solve()
    }
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
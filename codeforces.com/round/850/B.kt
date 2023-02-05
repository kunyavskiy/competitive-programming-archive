private fun IntArray.countOf(value: Int) = count { it == value }

private fun solve() {
    val s = "win"
    fun IntArray.bad() = (0 until 3).singleOrNull { c -> count { it == c } > 1 }
    val data = List(readInt()) { readLn().map { s.indexOf(it) }.toIntArray() }
    val ans = mutableListOf<String>()
    fun exchange(c1: Int, c2: Int, i1: Int, i2: Int) {
        ans.add("${i1+1} ${s[c1]} ${i2+1} ${s[c2]}")
        val index1 = data[i1].indexOf(c1)
        val index2 = data[i2].indexOf(c2)
        data[i1][index1] = c2
        data[i2][index2] = c1
    }
    val todo = List(3) { List(3) { mutableListOf<Int> () } }
    for (i in data.indices) {
        val bad = data[i].bad() ?: continue
        for (j in 0 until 3) {
            if (data[i].countOf(j) == 0) {
                todo[bad][j].add(i)
            }
        }
    }

    for (i in 0 until 3) {
        for (j in 0 until 3) {
            if (i != j) {
                while (todo[i][j].isNotEmpty() && todo[j][i].isNotEmpty()) {
                    exchange(i, j, todo[i][j].removeLast(), todo[j][i].removeLast())
                }
            }
        }
    }
    while (todo[0][1].isNotEmpty() && todo[1][2].isNotEmpty() && todo[2][0].isNotEmpty()) {
        val a = todo[0][1].removeLast()
        val b = todo[1][2].removeLast()
        val c = todo[2][0].removeLast()
        exchange(0, 1, a, b)
        exchange(0, 2, b, c)
    }
    while (todo[1][0].isNotEmpty() && todo[2][1].isNotEmpty() && todo[0][2].isNotEmpty()) {
        val a = todo[1][0].removeLast()
        val b = todo[2][1].removeLast()
        val c = todo[0][2].removeLast()
        exchange(1, 0, a, c)
        exchange(2, 1, b, c)
    }
    println(ans.size)
    println(ans.joinToString("\n"))
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
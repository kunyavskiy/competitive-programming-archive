private val pos = mutableMapOf<Long, Boolean>()



fun Long.unset(bit:Int) = this and (1L shl bit).inv()
fun Long.set(bit:Int) = this or (1L shl bit)

fun isWinning(n: Int, position: Long, g: LongArray) : Boolean = pos.getOrPut(position) {
    val v = (0 until n).filter { (position and (1L shl it)) != 0L }
    val cnt = v.count { it > 3 }
    if (cnt >= 5) {
        return@getOrPut isWinning(n, position.unset(v[v.size - 1]).unset(v[v.size - 2]), g)
    }

    for (i in v) {
        if (!isWinning(n, position.unset(i), g)) return@getOrPut true
        val msk = g[i] and position
        var m = msk
        while (m != 0L) {
            if (!isWinning(n, position.unset(i).and(m.inv()), g)) return@getOrPut true
            m = (m - 1) and msk
        }
    }

    return@getOrPut false
}

fun winningMove(n: Int, position: Long, g: LongArray) : List<Int>? {
    val v = toBits(n, position)
    for (i in (v.filter { it != 3 }) + (v.filter { it == 3 })){
        if (!isWinning(n, position.unset(i), g)) return listOf(i)
        val msk = g[i] and position
        var m = msk
        while (m != 0L) {
            if (!isWinning(n, position.unset(i).and(m.inv()), g)) return listOf(i) + toBits(n, msk)
            m = (m - 1) and msk
        }
    }
    return null
}

private fun toBits(n: Int, position: Long) = (0 until n).filter { (position and (1L shl it)) != 0L }

private fun solve() {
    pos.clear()
    val n = readInt()
    val g = LongArray(n)
    fun add(a: Int, b: Int) {
        g[a] = g[a].set(b)
        g[b] = g[b].set(a)
        println("${a + 1} ${b + 1}")
    }
    add(0, 1)
    add(1, 2)
    add(2, 3)
    for (i in 4 until n) {
        add(3, i)
    }
    require(!isWinning(n, (1L shl n) - 1, g)) { "Failed: move is ${winningMove(n, (1L shl n) - 1, g)}"}
    System.out.flush()
    val m = readInt()
    repeat(m) {
        var cur = (1L shl n) - 1

        while (true) {
            if (cur == 0L) break
            val k = readInt()
            val vs = readInts()
            for (i in vs) {
                cur = cur.unset(i - 1)
            }
            require(isWinning(n, cur, g))
            val bits = winningMove(n, cur, g)!!
            for (i in bits) {
                cur = cur.unset(i)
            }
            require(!isWinning(n, cur, g)) { "cur = ${toBits(n, cur) + bits}, move = ${bits}"}
            println(bits.size)
            println(bits.map { it + 1 }.joinToString(" "))
            System.out.flush()
        }
    }
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
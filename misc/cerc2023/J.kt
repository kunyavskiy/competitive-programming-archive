
fun main() {
    val (n, k) = readInts()
    val aa = List(k) { readInts() }
    val c = aa.map { it.first() }
    val d = aa.map { l -> l.drop(1).dropLastWhile { it == 0 }.toMutableList() }
    val ans = mutableListOf<Pair<Int, Int>>()

    fun op(a:Int, b:Int) {
        require(a != b)
        require(d[a].isNotEmpty())
        require(d[b].size < c[b])
        ans.add((a + 1) to (b + 1))
        d[b].add(d[a].last())
        d[a].removeAt(d[a].lastIndex)
    }

    fun compatLeft(lim: Int) {
        var lptr = 0
        for (i in 1 until lim) {
            while (lptr < i && d[i].isNotEmpty()) {
                while (c[lptr] == d[lptr].size) lptr++
                if (i > lptr) {
                    op(i, lptr)
                }
            }
        }
    }
    fun solve2() {
        require(d[1].isEmpty())
        for (i in 1..d[0].size) {
            while (d[0].last() != i) {
                op(0, 1)
            }
            val x : Int
            if (d[2].size == c[2]) {
                x = d[2].last()
                op(2, 1)
            } else {
                x = -1
            }
            op(0, 2)
            while (d[0].size != i - 1) {
                op(0, 1)
            }
            op(2, 0)
            while (d[1].isNotEmpty()) {
                if (d[1].last() == x) {
                    op(1, 2)
                } else {
                    op(1, 0)
                }
            }
        }
    }

    compatLeft(k)
    for (i in n downTo  1) {
        if (d[1].isEmpty() && d[2].size == c[2]) {
            solve2()
            break
        }
        val movedTo = mutableListOf<Int>()
        var rptr = k - 1
        val id = d.indexOfFirst { it.contains(i) }
        fun moveRight(from: Int) {
            while (d[rptr].size == c[rptr]) rptr--
            op(from, rptr)
            movedTo.add(rptr)
        }
        while (d[id].last() != i) {
            moveRight(id)
        }
        val other = d.indices.first { it != id }
        if (d[other].size == c[other]) moveRight(other)
        op(id, other)
        for (moved in movedTo) {
            if (moved != other)
                op(moved, id)
        }
        val rr = d.indices.last { d[it].size < c[it] }
        op(other, rr)
        compatLeft(rr)
    }
    compatLeft(k)
    require(d.flatten().withIndex().all { it.index + 1 == it.value })

    for ((a, b) in ans) {
        println("$a $b")
    }
    println("0 0")
}

private fun readInt() = readln().toInt()
private fun readLongs() = readStrings().map { it.toLong() }
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().filter { it.isNotEmpty() }.map { it.toInt() }
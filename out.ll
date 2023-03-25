; ModuleID = 'main'
source_filename = "main"

@.str = private constant [16 x i8] c"Hello world %d\0A\00"

declare i32 @printf(ptr, ...)

define void @main() {
entry:
  %0 = alloca [4 x i64], align 8
  store i64 1, ptr %0, align 8
  %1 = getelementptr inbounds i64, ptr %0, i64 1
  store i64 2, ptr %1, align 8
  %2 = getelementptr inbounds i64, ptr %0, i64 2
  store i64 3, ptr %2, align 8
  %3 = getelementptr inbounds i64, ptr %0, i64 3
  store i64 5, ptr %3, align 8
  br label %loop

loop:                                             ; preds = %entry, %loop
  %4 = phi i64 [ %6, %loop ], [ 5, %entry ]
  %5 = call i32 (ptr, ...) @printf(ptr noundef nonnull @.str, i64 %4)
  %6 = add i64 %4, -1
  store i64 %6, ptr %3, align 8
  %7 = icmp sgt i64 %6, 0
  br i1 %7, label %loop, label %continue

continue:                                         ; preds = %loop
  call void @printi(i64 1)
  ret void
}

declare void @printi(i64)

; ModuleID = 'main'
source_filename = "main"

@.str = private constant [5 x i8] c"yay\0A\00"
@.str.1 = private constant [5 x i8] c"boo\0A\00"
@.str.2 = private constant [12 x i8] c"count = %d\0A\00"
@str = private unnamed_addr constant [4 x i8] c"yay\00", align 1

declare i32 @printf(ptr, ...)

define void @main() {
entry:
  %puts = call i32 @puts(ptr nonnull @str)
  %count = alloca i64, align 8
  store i64 0, ptr %count, align 8
  br label %loop

loop:                                             ; preds = %entry, %loop
  %count3 = phi i64 [ %1, %loop ], [ 0, %entry ]
  %0 = call i32 (ptr, ...) @printf(ptr noundef nonnull @.str.2, i64 %count3)
  %1 = add i64 %count3, 1
  store i64 %1, ptr %count, align 8
  %2 = icmp slt i64 %1, 10
  br i1 %2, label %loop, label %continue1

continue1:                                        ; preds = %loop
  ret void
}

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr nocapture noundef readonly) #0

attributes #0 = { nofree nounwind }

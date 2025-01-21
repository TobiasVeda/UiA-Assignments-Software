using System.ComponentModel.DataAnnotations;

namespace assignment_3.Models;

public class Guest{
    
    public int Id{ get; set; }
    
    [Required]
    public string Name{ get; set; } = String.Empty;
    
    [Required] [MinLength(5)] [MaxLength(50)]
    public string Title{ get; set; } = String.Empty;
    
    [Required] [MinLength(20)] [MaxLength(200)]
    public string Message{ get; set; } = String.Empty;

    public Guest(){}
    public Guest(string name, string title, string message){
        Name = name;
        Title = title;
        Message = message;
    }

}